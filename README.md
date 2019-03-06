# ServerRecast

WARNING! This version was tested for compatibility with UE 4.21 version only!

UE4 plugin for navmesh export

Usage:

1. Clone https://github.com/darkwere/ServerRecast.git repo.
2. In ServerRecast folder run git command: git submodule update --init --remote
3. Put ServerRecast into [Your project]\Plugins folder.
4. In ServerRecast\recastnavigation folder look for readme.md file for instructions to build the solution. (Look down for explanations)
5. Open the level in Unreal Engine 4.
6. Put Navmesh Bounds Volume into the level.
7. Resize Navmesh Bounds Volume to fill all the necessary space in the level. You can check it by pressing 'P' key.
8. Press ServerRecast button in the top panel of Unreal Engine (it will appear there if you install the plugin successfully).
9. RecastDemo program will show up.
10. Select the type of sample mesh (solo mesh or tile mesh).
11. Select input mesh <YOUR_LEVEL_NAME>.obj
12. Press Build button.
13. Press Save after Build is finished.
14. solo_navmesh.bin or all_tiles_navmesh.bin (depends on selected sample) is your Navmesh file, now you can use it.

Explanations for p.4:
1. Put premake5.exe file into recastnavigation\RecastDemo folder.
2. Run "premake5.exe vs2017" at the command prompt.
3. Extract SDL library into recastnavigation\RecastDemo\Contrib folder and rename "SDL2-2.0.9" folder to "SDL".
4. Open recastnavigation.sln at recastnavigation\RecastDemo\Build\vs2017 folder with VS2017 and build solution.
5. Check RecastDemo.exe at recastnavigation\RecastDemo\bin folder, run and test it with build-in meshes.