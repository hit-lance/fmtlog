#define FMTLOG_HEADER_ONLY

#include <thread>

#include "fmt/format.h"
#include "fmtlog.h"

void runBenchmark();

int main() {
  fmtlog::startPollingThread();

  fmtlog::setLogLevel(fmtlog::DBG);

  auto th1 = std::thread([] {
    fmtlog::Logger* logger1 = fmtlog::getLogger("stdout");
    logd(logger1, "logger2 The answer is {}.", 1);
    logdo(logger1, "logger2 The answer is {}.", 2);
    logi(logger1, "logger2 The answer is {}.", 3);
    logio(logger1, "logger2 The answer is {}.", 4);
    logw(logger1, "logger2 The answer is {}.", 5);
    logwo(logger1, "logger2 The answer is {}.", 6);
    loge(logger1, "logger2 The answer is {}.", 7);
    logeo(logger1, "logger2 The answer is {}.", 8);
  });
  auto th2 = std::thread([] {
    fmtlog::Logger* logger2 = fmtlog::getLogger("stdout");
    logd(logger2, "logger2 The answer is {}.", 1);
    logdo(logger2, "logger2 The answer is {}.", 2);
    logi(logger2, "logger2 The answer is {}.", 3);
    logio(logger2, "logger2 The answer is {}.", 4);
    logw(logger2, "logger2 The answer is {}.", 5);
    logwo(logger2, "logger2 The answer is {}.", 6);
    loge(logger2, "logger2 The answer is {}.", 7);
    logeo(logger2, "logger2 The answer is {}.", 8);
  });

  th1.join();
  th2.join();
  // fmtlog::Logger* logger1 = fmtlog::getLogger("stdout");
  // logio(logger1, "The answer is {}.", 2);
  // fmtlog::poll(true);

  // runBenchmark();
  return 0;
}

void runBenchmark() {
  fmtlog::Logger* logger = fmtlog::getLogger("/dev/null");

  const int RECORDS = 100000000;
  // fmtlog::setLogFile("/dev/null", false);
  fmtlog::setLogCB(nullptr, fmtlog::WRN);

  std::chrono::high_resolution_clock::time_point t0, t1;

  t0 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < RECORDS; ++i) {
    logi(logger, "Simple log message with one parameters, {}", i);
  }
  t1 = std::chrono::high_resolution_clock::now();

  double span = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t0).count();
  fmt::print("benchmark, front latency: {:.1f} ns/msg average\n", (span / RECORDS) * 1e9);
  abort();
}
