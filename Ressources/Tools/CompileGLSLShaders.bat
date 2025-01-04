set GLSLANG_PATH=%CD%\ThirdParty
for %%i in ("%CD%\..\Shaders") do (
	set SHADER_PATH=%%~fi
)

cd %SHADER_PATH%
rmdir /S /Q bin
mkdir bin

for %%f in (*.glsl*) do (
	 %GLSLANG_PATH%\glslangValidator -V %%f -o bin/%%~nf.spv
)






