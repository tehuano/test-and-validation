#! python3

import os

modelsim_path = 'D:/altera/13.1/modelsim_ase/win32aloem/'
test_script = 'gpio_hsm_tb.do'

def run(cmd):
    print(cmd)
    os.system(cmd)

cmd = modelsim_path + 'modelsim.exe' + ' -do ' + test_script
#+ os.path.dirname(os.path.abspath(test_script).replace('\\', '/')) + '/}"' + ' -do "do ' +  + '"'
run(cmd)