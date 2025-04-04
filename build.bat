set /p CppFilename=Enter the name of the cpp file: 
set /p ExeFilename=Enter the name of the executable file: 
cl /FC /Zi /EHsc /fsanitize=address -Fe:%ExeFilename% %CppFilename%.cpp -link user32.lib gdi32.lib