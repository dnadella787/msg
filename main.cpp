#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

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

    spdlog::info("Hello, World!");

    return 0;
}