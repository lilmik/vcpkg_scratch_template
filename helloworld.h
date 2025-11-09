#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <CSerialPort/SerialPort.h>
#include <vector>
#include <QDebug>

// 必须继承 QObject + Q_OBJECT 宏（信号槽必需）
class SignalSlotDemo : public QObject
{
    Q_OBJECT

public:
    explicit SignalSlotDemo(QObject *parent = nullptr);

public slots:
    void onTimerTimeout(); // 槽函数声明

private:
    int m_counter = 0; // 触发计数器
};

#endif // HELLOWORLD_H
