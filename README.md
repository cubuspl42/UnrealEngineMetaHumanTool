# UnrealEngineMetaHumanTool

## Setup

This directory must be located alongside `UnrealEngine` root directory (i.e. in the same parent directory as that one).

This tools expects minor modifications to the engine's code ([from this branch](https://github.com/cubuspl42/UnrealEngine/tree/metahuman-standalone)).

The `UE5` project must be built.

## Project configuration

### Compilation

- Preprocessor definitions: See `preprocessor_definitions.txt`
  - Visual Studio setting: C/C++ > Preprocessor > Preprocessor Definitions 
- Include paths: See `include_paths.txt`
  - Visual Studio setting: C/C++ > General > Additional Include Directories

### Linking

- Input: `UnrealEditor-MetaHumanCoreTechLib.lib`
  - Visual Studio setting: Linker > Input > Additional Library Directories
- Library paths: See `lib_paths.txt`
  - Visual Studio setting: Linker > General > Additional Library Directories

### Runtime paths

- Runtime DLL paths: See `runtime_paths.txt`
  - Visual Studio setting: Debugging > Environment (`PATH=%PATH%:<extra paths>`)

## Procmon

### `Load Image` filter:

- `Process Name` / `is` / `UnrealEditor.exe`
- `Operation` / `is` / `Load Image`

## Python utils

See `utils/`
