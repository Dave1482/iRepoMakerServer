include theos/makefiles/common.mk

TOOL_NAME = RepoMakerServer
RepoMakerServer_FILES = main.c mongoose.c
RepoMakerServer_FRAMEWORKS = CoreFoundation

include $(THEOS_MAKE_PATH)/tool.mk
