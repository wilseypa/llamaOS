
MAKE_SOURCES = supc++.mk common.mk rules.mk

include common.mk

CPPFLAGS += -include glibc/include/libc-symbols.h

INCLUDES = \
  glibc/include \
  glibc/sysdeps/llamaos \
  glibc/sysdeps/x86_64 \
  glibc/sysdeps/ieee754/ldbl-128 \
  glibc/sysdeps/ieee754 \
  glibc/sysdeps/generic \
  glibc/libio \
  glibc \
  gcc/include \
  gcc \
  gcc/libstdc++-v3/include/c_global \
  gcc/libstdc++-v3/include/std \
  gcc/libstdc++-v3/include \
  gcc/libstdc++-v3/libsupc++

CPPFLAGS += $(INCLUDES:%=-I %)

VPATH = src

#  gcc/libstdc++-v3/libsupc++/eh_ptr.cc \

SOURCES = \
  gcc/libstdc++-v3/libsupc++/array_type_info.cc \
  gcc/libstdc++-v3/libsupc++/bad_alloc.cc \
  gcc/libstdc++-v3/libsupc++/bad_cast.cc \
  gcc/libstdc++-v3/libsupc++/bad_typeid.cc \
  gcc/libstdc++-v3/libsupc++/class_type_info.cc \
  gcc/libstdc++-v3/libsupc++/del_op.cc \
  gcc/libstdc++-v3/libsupc++/del_opnt.cc \
  gcc/libstdc++-v3/libsupc++/del_opv.cc \
  gcc/libstdc++-v3/libsupc++/del_opvnt.cc \
  gcc/libstdc++-v3/libsupc++/dyncast.cc \
  gcc/libstdc++-v3/libsupc++/eh_alloc.cc \
  gcc/libstdc++-v3/libsupc++/eh_aux_runtime.cc \
  gcc/libstdc++-v3/libsupc++/eh_call.cc \
  gcc/libstdc++-v3/libsupc++/eh_catch.cc \
  gcc/libstdc++-v3/libsupc++/eh_exception.cc \
  gcc/libstdc++-v3/libsupc++/eh_globals.cc \
  gcc/libstdc++-v3/libsupc++/eh_personality.cc \
  gcc/libstdc++-v3/libsupc++/eh_term_handler.cc \
  gcc/libstdc++-v3/libsupc++/eh_terminate.cc \
  gcc/libstdc++-v3/libsupc++/eh_throw.cc \
  gcc/libstdc++-v3/libsupc++/eh_type.cc \
  gcc/libstdc++-v3/libsupc++/eh_unex_handler.cc \
  gcc/libstdc++-v3/libsupc++/enum_type_info.cc \
  gcc/libstdc++-v3/libsupc++/function_type_info.cc \
  gcc/libstdc++-v3/libsupc++/fundamental_type_info.cc \
  gcc/libstdc++-v3/libsupc++/guard.cc \
  gcc/libstdc++-v3/libsupc++/guard_error.cc \
  gcc/libstdc++-v3/libsupc++/hash_bytes.cc \
  gcc/libstdc++-v3/libsupc++/nested_exception.cc \
  gcc/libstdc++-v3/libsupc++/new_handler.cc \
  gcc/libstdc++-v3/libsupc++/new_op.cc \
  gcc/libstdc++-v3/libsupc++/new_opnt.cc \
  gcc/libstdc++-v3/libsupc++/new_opv.cc \
  gcc/libstdc++-v3/libsupc++/new_opvnt.cc \
  gcc/libstdc++-v3/libsupc++/pbase_type_info.cc \
  gcc/libstdc++-v3/libsupc++/pmem_type_info.cc \
  gcc/libstdc++-v3/libsupc++/pointer_type_info.cc \
  gcc/libstdc++-v3/libsupc++/pure.cc \
  gcc/libstdc++-v3/libsupc++/si_class_type_info.cc \
  gcc/libstdc++-v3/libsupc++/tinfo.cc \
  gcc/libstdc++-v3/libsupc++/tinfo2.cc \
  gcc/libstdc++-v3/libsupc++/vec.cc \
  gcc/libstdc++-v3/libsupc++/vmi_class_type_info.cc \
  gcc/libstdc++-v3/libsupc++/vterminate.cc

BINARY = supc++.a
OBJECTS = $(SOURCES:%.cc=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

$(LIBDIR)/$(BINARY) : $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif
