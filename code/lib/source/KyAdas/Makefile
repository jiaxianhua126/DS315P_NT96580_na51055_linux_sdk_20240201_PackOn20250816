include $(NVT_PRJCFG_MODEL_CFG)
MODULE_NAME = libKyAdas
OUTPUT_DIR = $(LIBRARY_DIR)/output
###############################################################################
# Linux Makefile                                                              #
###############################################################################
ifeq ($(NVT_PRJCFG_CFG),Linux)
all:
	@echo "Building $(MODULE_NAME)'"

install:
	@mkdir -p $(OUTPUT_DIR)
	@cp -avf *.a $(OUTPUT_DIR)
	@mkdir -p $(ROOTFS_DIR)/rootfs/data/adas/model_file/
	@mkdir -p $(ROOTFS_DIR)/rootfs/data/adas/config_file/
	@cp -avfr model_file/* $(ROOTFS_DIR)/rootfs/data/adas/model_file/
endif

clean:
	@echo "Clean '$(MODULE_NAME)'"
