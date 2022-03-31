#//***********************************************************/
project(
    'c_dbg',          ['c'],         version : '0.0.1',         
    default_options : ['warning_level=2','c_std=gnu99'],
)
#//***********************************************************/
host_system = host_machine.system()

cc = meson.get_compiler('c')
sh = find_program('sh', required : true)
passh = find_program('passh', required : true)

#//***********************************************************/
test_deps = []
#//***********************************************************/
incdir = include_directories(
  './include', 
  './src', 
  './deps', 
  '../',
  '../metalang99/include',
  '../ok',
)
#//***********************************************************/
test_dbg1 = executable('test_dbg1', [ 
    'tests/test_dbg1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
#//***********************************************************/
tests = [
  ['test dbg 1', test_dbg1, 'test-dbg-1.log'],
]
#//***********************************************************/

#//***********************************************************/
test_env = environment()
test_env.set('__SH', sh.full_path())
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
#//***********************************************************/
foreach i : tests
test(i[0], passh, args: ['-L', i[2], i[1] ], env: test_env)
endforeach
#//***********************************************************/


