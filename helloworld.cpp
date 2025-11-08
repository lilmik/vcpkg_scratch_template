#include <iostream>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <CSerialPort/SerialPort.h>

// 给库起别名，简化代码
using json = nlohmann::json;

int main()
{
    // 演示 fmt 的高级格式化功能
    std::cout << fmt::format("\n{}", "✨ fmt Formatting Examples " + std::string(20, '=')) << std::endl;

    itas109::CSerialPort *m_SerialPort = new itas109::CSerialPort();

    delete m_SerialPort;

    // 使用 fmt 格式化指针信息
    std::cout << fmt::format("📍 Pointer address: {:p}", static_cast<void *>(m_SerialPort)) << std::endl;
    std::cout << fmt::format("📏 Pointer size: {} bytes", sizeof(m_SerialPort)) << std::endl;
    std::cout << fmt::format("📦 Object size: {} bytes", sizeof(*m_SerialPort)) << std::endl;

    // 使用 nlohmann/json 创建指针信息报告
    nlohmann::json pointerInfo = {
        {"pointer_address", fmt::format("{:p}", static_cast<void *>(m_SerialPort))},
        {"pointer_size_bytes", sizeof(m_SerialPort)},
        {"object_size_bytes", sizeof(*m_SerialPort)},
        {"library", "CSerialPort"},
        {"namespace", "itas109"},
        {"type", "CSerialPort*"}};

    std::cout << "\n📄 Pointer Information:\n"
              << pointerInfo.dump(2) << std::endl;

    return 0;
}