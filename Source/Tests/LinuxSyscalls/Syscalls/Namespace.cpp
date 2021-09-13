/*
$info$
tags: LinuxSyscalls|syscalls-shared
$end_info$
*/

#include "Tests/LinuxSyscalls/Syscalls.h"
#include "Tests/LinuxSyscalls/Syscalls/Thread.h"
#include "Tests/LinuxSyscalls/x64/Syscalls.h"
#include "Tests/LinuxSyscalls/x32/Syscalls.h"

#include <signal.h>
#include <sys/syscall.h>
#include <unistd.h>

namespace SignalDelegator {
  struct GuestSigAction;
}


namespace FEX::HLE {
  void RegisterNamespace(FEX::HLE::SyscallHandler *const Handler) {
    if (Handler->GetHostKernelVersion() >= FEX::HLE::SyscallHandler::KernelVersion(5, 1, 0)) {
      REGISTER_SYSCALL_IMPL(open_tree, [](FEXCore::Core::CpuStateFrame *Frame, int dfd, const char *filename, unsigned int flags) -> uint64_t {
        uint64_t Result = ::syscall(SYS_open_tree, dfd, filename, flags);
        SYSCALL_ERRNO();
      });

      REGISTER_SYSCALL_IMPL(move_mount, [](FEXCore::Core::CpuStateFrame *Frame, int from_dfd, const char *from_pathname, int to_dfd, const char *to_pathname, unsigned int flags) -> uint64_t {
        uint64_t Result = ::syscall(SYS_move_mount, from_dfd, from_pathname, to_dfd, to_pathname, flags);
        SYSCALL_ERRNO();
      });

      REGISTER_SYSCALL_IMPL(fsopen, [](FEXCore::Core::CpuStateFrame *Frame, int dfd, const char *path, unsigned int flags) -> uint64_t {
        uint64_t Result = ::syscall(SYS_fsopen, dfd, path, flags);
        SYSCALL_ERRNO();
      });

      REGISTER_SYSCALL_IMPL(fsconfig, [](FEXCore::Core::CpuStateFrame *Frame, int fd, unsigned int cmd, const char *key, const void *value, int aux) -> uint64_t {
        uint64_t Result = ::syscall(SYS_fsconfig, fd, cmd, key, value, aux);
        SYSCALL_ERRNO();
      });

      REGISTER_SYSCALL_IMPL(fspick, [](FEXCore::Core::CpuStateFrame *Frame, int dfd, const char *path, unsigned int flags) -> uint64_t {
        uint64_t Result = ::syscall(SYS_fspick, dfd, path, flags);
        SYSCALL_ERRNO();
      });
    }
    else {
      REGISTER_SYSCALL_IMPL(open_tree, UnimplementedSyscallSafe);
      REGISTER_SYSCALL_IMPL(move_mount, UnimplementedSyscallSafe);
      REGISTER_SYSCALL_IMPL(fsopen, UnimplementedSyscallSafe);
      REGISTER_SYSCALL_IMPL(fsconfig, UnimplementedSyscallSafe);
      REGISTER_SYSCALL_IMPL(fsmount, UnimplementedSyscallSafe);
      REGISTER_SYSCALL_IMPL(fspick, UnimplementedSyscallSafe);
    }

#ifndef SYS_mount_setattr
#define SYS_mount_setattr 442
#endif
    if (Handler->GetHostKernelVersion() >= FEX::HLE::SyscallHandler::KernelVersion(5, 12, 0)) {
      REGISTER_SYSCALL_IMPL(mount_setattr, [](FEXCore::Core::CpuStateFrame *Frame, int dfd, const char *path, unsigned int flags, void *uattr, size_t usize) -> uint64_t {
        uint64_t Result = ::syscall(SYS_mount_setattr, dfd, path, flags, uattr, usize);
        SYSCALL_ERRNO();
      });
    }
    else {
      REGISTER_SYSCALL_IMPL(mount_setattr, UnimplementedSyscallSafe);
    }
  }
}