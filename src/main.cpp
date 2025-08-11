#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>
#include <grpcpp/grpcpp.h>
#include "stock.grpc.pb.h"

class StockMarketClient {
public:
    explicit StockMarketClient(const std::shared_ptr<grpc::Channel>& channel) : stub_(StockMarket::NewStub(channel)) {}

    [[nodiscard]] float GetPrice(const std::string& symbol) const {
        GetStockRequest request;
        request.set_symbol(symbol);

        GetStockResponse response;
        grpc::ClientContext context;

        grpc::Status status = stub_->GetStock(&context, request, &response);
        if (!status.ok()) {
            spdlog::error("GetStock request failed with message={}, details={}", status.error_message(), status.error_details());
            return -1;
        }
        spdlog::info("Successful GetStock response with current_price={}, pe_ratio={}", response.current_price(), response.current_pe_ratio());
        return response.current_price();
    }

private:
    std::unique_ptr<StockMarket::Stub> stub_;
};

int main(const int argc, char* argv[]) {
    // Flag assignment variables
    bool debug_log = false;

    CLI::App app{"Messaging client CLI"};
    app.add_flag("-d,--debug", debug_log, "Enable debug logging");
    try {
        app.parse(argc, argv);
        spdlog::set_level(debug_log ? spdlog::level::debug : spdlog::level::info);
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }

    spdlog::info("Initiating stock market gRPC client creation");
    StockMarketClient client(grpc::CreateChannel(
    "127.0.0.1:21000", grpc::InsecureChannelCredentials()));

    const std::string voo_sym("VOO");
    if (double price = client.GetPrice(voo_sym); price >= 0)
        spdlog::info("Price of {} is {}", voo_sym, price);
    else
        spdlog::error("GetStock returned error for sym {}", voo_sym);

    return 0;
}