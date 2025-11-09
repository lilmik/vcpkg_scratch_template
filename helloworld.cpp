#include "helloworld.h"
#include <QCoreApplication>
#include <iostream>

// 实现头文件中的构造函数
SignalSlotDemo::SignalSlotDemo(QObject *parent)
    : QObject(parent)
{
}

void SignalSlotDemo::onTimerTimeout()
{
    m_counter++;
    fmt::print("\n=== 槽函数触发第 {} 次 ===\n", m_counter);

    // 修复 1：QTimer 无 currentTime 接口，改用 QDateTime 获取时间戳
    nlohmann::json status_json;
    status_json["trigger_count"] = m_counter;
    status_json["timestamp_ms"] = QDateTime::currentMSecsSinceEpoch();
    status_json["status"] = "running";
    fmt::print("槽函数生成 JSON: {}\n", status_json.dump(2));

    // 演示 fmt 的高级格式化功能（保留你的核心需求）
    std::cout << fmt::format("\n{}", "✨ fmt Formatting Examples " + std::string(20, '=')) << std::endl;

    itas109::CSerialPort *m_SerialPort = new itas109::CSerialPort();

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

    delete m_SerialPort; // 释放内存，避免泄漏

    // 触发 5 次后退出
    if (m_counter >= 5)
    {
        fmt::print("\n触发次数达标，退出程序...\n");
        QCoreApplication::quit();
    }
}

// 主函数（无修改，保持原逻辑）
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    SignalSlotDemo demo;
    QTimer timer;

    // 信号槽连接（Qt6 类型安全语法）
    QObject::connect(&timer, &QTimer::timeout, &demo, &SignalSlotDemo::onTimerTimeout);

    timer.setInterval(1000); // 1秒触发一次
    timer.start();
    fmt::print("程序启动成功！将每 1 秒触发一次槽函数（共 5 次）\n");

    return app.exec();
}
