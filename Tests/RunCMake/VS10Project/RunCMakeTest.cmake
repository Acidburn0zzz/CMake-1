include(RunCMake)
cmake_policy(SET CMP0054 NEW)

run_cmake(VsCSharpCompilerOpts)
run_cmake(ExplicitCMakeLists)
run_cmake(RuntimeLibrary)
run_cmake(SourceGroupCMakeLists)

run_cmake(VsConfigurationType)
run_cmake(VsTargetsFileReferences)
run_cmake(VsCustomProps)
run_cmake(VsDebuggerWorkingDir)
run_cmake(VsDebuggerCommand)
run_cmake(VsDebuggerCommandArguments)
run_cmake(VsDebuggerEnvironment)
run_cmake(VsCSharpCustomTags)
run_cmake(VsCSharpReferenceProps)
run_cmake(VsCSharpWithoutSources)
run_cmake(VsCSharpDeployFiles)
run_cmake(VSCSharpDefines)
run_cmake(VsSdkDirectories)
run_cmake(VsGlobals)
run_cmake(VsProjectImport)
run_cmake(VsPackageReferences)
run_cmake(VsDpiAware)
run_cmake(VsDpiAwareBadParam)

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC" AND CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL 19.05)
  run_cmake(VsJustMyCode)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC" AND CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL 19.20)
  run_cmake(VsSpectreMitigation)
endif()
