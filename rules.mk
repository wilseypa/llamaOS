
$(OBJDIR)/%.o : %.S
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo compiling: $<
	@$(CC) -c $(ASMFLAGS) -o $@ $<

$(OBJDIR)/%.o : %.c
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo compiling: $<
	@$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o : %.cc
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo compiling: $<
	@$(CC) -c $(CPPFLAGS) -o $@ $<

$(OBJDIR)/%.o : %.cpp
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
