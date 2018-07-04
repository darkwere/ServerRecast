# ServerRecast
UE4 plugin for navmesh export

Usage:

1. Clone https://github.com/darkwere/ServerRecast.git repo.
2. In ServerRecast folder run git command: git submodule update --init --remote
3. Put ServerRecast into [Your project]\Plugins folder.
4. In ServerRecast\recastnavigation folder look for readme.md file for instructions to build the solution.
5. Open the level in Unreal Engine 4.
6. Put Navmesh Bounds Volume into the level.
7. Resize Navmesh Bounds Volume to fill all the necessary space in the level. You can check it by pressing 'P' key.
8. Press ServerRecast button in the top panel of Unreal Engine (it will appear there if you install the plugin successfully).
9. RecastDemo program will show up.
10. Select the type of sample mesh (solo mesh or tile mesh).
11. Press Build button.
12. Press Save after Build is finished.
13. all_tiles_navmesh.bin is your Navmesh file, now you can use it.
