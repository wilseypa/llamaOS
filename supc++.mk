
include common.mk
MAKEFILE_SOURCES += supc++.mk

VPATH = gcc/libstdc++-v3/libsupc++

#  gcc/libstdc++-v3/libsupc++/eh_ptr.cc \

SOURCES = \
  array_type_info.cc \
  bad_alloc.cc \
  bad_cast.cc \
  bad_typeid.cc \
  class_type_info.cc \
  del_op.cc \
  del_opnt.cc \
  del_opv.cc \
  del_opvnt.cc \
  dyncast.cc \
  eh_alloc.cc \
  eh_aux_runtime.cc \
  eh_call.cc \
  eh_catch.cc \
  eh_exception.cc \
  eh_globals.cc \
  eh_personality.cc \
  eh_term_handler.cc \
  eh_terminate.cc \
  eh_throw.cc \
  eh_type.cc \
  eh_unex_handler.cc \
  enum_type_info.cc \
  function_type_info.cc \
  fundamental_type_info.cc \
  guard.cc \
  guard_error.cc \
  hash_bytes.cc \
  nested_exception.cc \
  new_handler.cc \
  new_op.cc \
  new_opnt.cc \
  new_opv.cc \
  new_opvnt.cc \
  pbase_type_info.cc \
  pmem_type_info.cc \
  pointer_type_info.cc \
  pure.cc \
  si_class_type_info.cc \
  tinfo.cc \
  tinfo2.cc \
  vec.cc \
  vmi_class_type_info.cc \
  vterminate.cc

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
