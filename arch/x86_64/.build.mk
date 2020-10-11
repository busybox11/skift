CC:=x86_64-pc-skift-gcc
CXX:=x86_64-pc-skift-g++
LD:=x86_64-pc-skift-ld
AR:=x86_64-pc-skift-ar
AS:=nasm
ASFLAGS:=-f elf64

KERNEL_CXXFLAGS += \
	-fno-pic                       \
	-mno-sse                       \
	-mno-sse2                      \
	-mno-mmx                       \
	-mno-80387                     \
	-mno-red-zone                  \
	-mcmodel=kernel                \
	-ffreestanding                 \
	-fno-stack-protector           \
	-fno-omit-frame-pointer

KERNEL_SOURCES += $(wildcard arch/x86/kernel/*.cpp)
KERNEL_ASSEMBLY_SOURCES += $(wildcard arch/x86/kernel/*.s)
