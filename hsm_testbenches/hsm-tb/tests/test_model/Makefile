MODELSIM_PATH=/opt/intelFPGA/19.1/modelsim_ase/bin
UVM_PATH=/opt/intelFPGA/19.1/modelsim_ase/uvm-1.2

build: clean
	${MODELSIM_PATH}/vlog -work work -sv +incdir+${UVM_PATH}/src +define+UVM_NO_DPI ${UVM_PATH}/src/uvm_pkg.sv top.sv external.cpp
clean:
	rm -rf DVEfiles csrc simv simv.daidir ucli.key .vlogansetup.args .vlogansetup.env .vcs_lib_lock simv.vdb AN.DB vc_hdrs.h *.diag *.vpd *tar.gz external.o work

sim:
	${MODELSIM_PATH}/vsim work.top
