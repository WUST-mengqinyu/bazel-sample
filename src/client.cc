//
// Created by 孟钦宇 on 2021/7/15.
// Here is Client
//

// internal stl
#include <vector>

// lib outside
#include <fmt/core.h>
#include <grpcpp/grpcpp.h>

// user lib
#include "proto/hello.grpc.pb.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;
using helloworld::Hello;
using helloworld::Request;
using helloworld::Response;

class HelloClient {
public:
    explicit HelloClient(const std::shared_ptr<Channel> &channel)
            : stub_(Hello::NewStub(channel)) {}

    void GetRep(const std::string &name) {
        ClientContext context;
        auto stream = stub_->GetKey(&context);
        Request req;
        req.set_name(name);
        fmt::print("client: start to send request to server: {}\n", name);
        stream->Write(req);
        Response res;
        stream->Read(&res);
        fmt::print("client: receive from server: {}, {}\n", name, res.message());
        stream->WritesDone();
        Status status = stream->Finish();
        if (!status.ok()) {
            fmt::print("client: RPC failed, error code: {}, error message: {}.\n", status.error_code(),
                       status.error_message());
        }
    }

private:
    std::unique_ptr<Hello::Stub> stub_;
};

int main(int argc, char *argv[]) {
    HelloClient client(grpc::CreateChannel("127.0.0.1:50001", grpc::InsecureChannelCredentials()));
    std::vector<std::string> names = {
            "test2", "empty", "", "ttt2"
    };
    for (const auto &name : names) {
        client.GetRep(name);
    }
    return 0;
}
