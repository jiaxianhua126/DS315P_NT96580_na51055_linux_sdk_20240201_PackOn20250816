include $(NVT_PRJCFG_MODEL_CFG)
MODULE_NAME = libASR
OUTPUT_DIR = $(LIBRARY_DIR)/output
###############################################################################
# Linux Makefile                                                              #
###############################################################################
ifeq ($(NVT_PRJCFG_CFG),Linux)
all:
	@echo "Building $(MODULE_NAME)'"

install:
#	@echo $(OUTPUT_DIR)
#	@echo $(ROOTFS_DIR)
	@mkdir -p $(OUTPUT_DIR)
	@cp -avf *.a $(OUTPUT_DIR)
	@mkdir -p $(ROOTFS_DIR)/rootfs/root/res
	@mkdir -p $(ROOTFS_DIR)/rootfs/root/test
	@cp -avfr res/* $(ROOTFS_DIR)/rootfs/root/res/
	@cp -avfr test/* $(ROOTFS_DIR)/rootfs/root/test/
endif

clean:
	@echo "Clean '$(MODULE_NAME)'"
