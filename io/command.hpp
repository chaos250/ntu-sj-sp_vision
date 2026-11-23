#ifndef IO__COMMAND_HPP
#define IO__COMMAND_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace io
{
// 工作模式枚举（io/command.hpp 统一定义，CBoard/CBoard1 共用）。
// 保持 unscoped enum，便于 io::MODES[mode] 直接索引。
// 注意：前 4 个值（0~3）与电控 CAN 状态帧的 mode 位一一对应，
// auto_buff 为 USB CDC 协议新增值，只能追加在末尾，不能插入中间。
enum Mode { idle, auto_aim, small_buff, big_buff, outpost, auto_buff };

// 模式名称（用于日志输出），定义见 io/command.cpp
extern const std::vector<std::string> MODES;

// 视觉发给电控的命令结构体
// 兼容 XDU 上游的聚合初始化 io::Command{control, shoot, yaw, pitch}
struct Command
{
  Command() = default;
  Command(bool control, bool shoot, double yaw, double pitch)
    : control(control), shoot(shoot), yaw(yaw), pitch(pitch) {}

  bool control = false;           // 是否开启云台控制
  bool shoot = false;             // 是否开火
  float yaw = 0.0f;               // 目标 yaw 角度 (rad)
  float pitch = 0.0f;             // 目标 pitch 角度 (rad)
  float horizon_distance = 0.0f;  // 水平距离 (m)，无人机专有

  // 扩展字段用于填充 SendPacket（USB CDC 协议，见 io/protocol.hpp）
  float target_x = 0.0f;
  float target_y = 0.0f;
  float target_z = 0.0f;
  float target_vx = 0.0f;
  float target_vy = 0.0f;
  float target_vz = 0.0f;
  float target_yaw = 0.0f;
  float target_v_yaw = 0.0f;
  float r1 = 0.12f;
  float r2 = 0.12f;
  float dz = 0.0f;
  bool tracking = false;
  uint8_t id = 0;
  uint8_t armors_num = 4;
};

}  // namespace io

#endif  // IO__COMMAND_HPP
