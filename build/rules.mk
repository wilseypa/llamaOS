#
# Copyright (c) 2012, William Magato
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    1. Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
#
#    2. Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS
# ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# The views and conclusions contained in the software and documentation are
# those of the authors and should not be interpreted as representing official
# policies, either expressed or implied, of the copyright holder(s) or
# contributors.
#

$(OBJDIR)/%.o : %.S $(MAKEFILE_SOURCES)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo compiling: $<
	@$(CC) -c $(ASMFLAGS) -o $@ $<

$(OBJDIR)/%.o : %.c $(MAKEFILE_SOURCES)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo compiling: $<
	@$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o : %.cc $(MAKEFILE_SOURCES)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo compiling: $<
	@$(CC) -c $(CPPFLAGS) -o $@ $<

$(OBJDIR)/%.o : %.cpp $(MAKEFILE_SOURCES)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo compiling: $<
	@$(CC) -c $(CPPFLAGS) -o $@ $<

$(OBJDIR)/%.d : %.S
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo creating: $@ from $<
	@$(CC) $(ASMFLAGS) -MM -MP -MT '$(OBJDIR)/$*.o $(OBJDIR)/$*.d' -MF $@ $<

$(OBJDIR)/%.d : %.c
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo creating: $@ from $<
	@$(CC) $(CFLAGS) -MM -MP -MT '$(OBJDIR)/$*.o $(OBJDIR)/$*.d' -MF $@ $<

$(OBJDIR)/%.d : %.cc
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo creating: $@ from $<
	@$(CC) $(CPPFLAGS) -MM -MP -MT '$(OBJDIR)/$*.o $(OBJDIR)/$*.d' -MF $@ $<

$(OBJDIR)/%.d : %.cpp
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo creating: $@ from $<
	@$(CC) $(CPPFLAGS) -MM -MP -MT '$(OBJDIR)/$*.o $(OBJDIR)/$*.d' -MF $@ $<