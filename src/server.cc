//
// Created by 孟钦宇 on 2021/7/15.
// Here is Server
//

// internal stl
#include <string>
#include <random>
#include <unistd.h>

// lib outside
#include <fmt/core.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/health_check_service_interface.h>
#include "sqlite3.h"

// user lib
#include "proto/hello.grpc.pb.h"
#include "utils/utils.h"

using helloworld::Hello;
using helloworld::Request;
using helloworld::Response;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerReaderWriter;

#define ERROR_MSG_READ_DATA_FAIL "error when read message from proto stream"
#define ERROR_MSG_EMPTY_NAME "can't request an empty name"

std::mt19937 myrand(time(nullptr));;

class HelloImpl final : public Hello::Service {
public:
    explicit HelloImpl(sqlite3 *db) : db(db) {}

    Status GetKey(::grpc::ServerContext *context,
                  ::grpc::ServerReaderWriter<::helloworld::Response, ::helloworld::Request> *stream) override {
        fmt::print("server: receive from client.\n");
        Request req;
        Status res = Status::OK;
        do {
            if (!stream->Read(&req)) {
                res = Status(grpc::ABORTED, ERROR_MSG_READ_DATA_FAIL);
                break;
            }
            if (req.name().empty()) {
                res = Status(grpc::ABORTED, ERROR_MSG_EMPTY_NAME);
                break;
            }
            fmt::print("server: get message \"{}\"\n", req.name().c_str());
            fmt::print("server: start write message \"hello {}\" to stream\n", req.name().c_str());
            Response rsp;
            rsp.set_message(fmt::format("hello {}, your is: {}", req.name(), deal_with_message(req.name())));
            stream->Write(rsp);
            fmt::print("server: success write message \"hello {}\" to stream\n", req.name().c_str());
        } while (false);
        fmt::print("server: done for client.\n");
        return res;
    }

private:
    sqlite3 *db;

    std::string deal_with_message(const std::string &name) {
        fmt::print("server: deal with message now.\n");
        std::string val;
        if (utils::GetDB(db, name, &val) != SQLITE_OK) {
            for (int i = 0; i < 10; ++i) {
                val += (myrand() % 10) + '0';
            }
            fmt::print("server: can't search {} in db, create a new one now {}.\n", name, val);
            if (utils::PutDB(db, name, val) == SQLITE_OK) {
                fmt::print("server: save {}:{} success.\n", name, val);
            }
        }
        fmt::print("server: down with message now. {}:{}\n", name, val);
        return val;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50001");

    // init a impl class
    sqlite3 *db;
    utils::CreateDB("./data.db", &db);
    HelloImpl service(db);

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    // init a builder
    ServerBuilder builder;
    // set builder address and credential
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // register service to build
    builder.RegisterService(&service);

    // start a truly server by builder
    std::unique_ptr<Server> server(builder.BuildAndStart());
    fmt::print("Server listening on {}\n", server_address);

    server->Wait();
}

void print_wrk_dir() {
    char buffer[250];
    getcwd(buffer, 250);
    fmt::print("The current directory is: {}\n", buffer);
}

int main(int argc, char *argv[]) {
    print_wrk_dir();
    RunServer();
    return 0;
}
