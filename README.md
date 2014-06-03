Space Station Keeper
====================

Overview
--------
Working title for a game which will basically be a clone of Dungeon Keeper but on an asteroid. I am working on it mostly to learn c++/graphics programming which is why I didn't use an existing game engine which would have cut the project time significantly. 

The game engine is fully generic and almost ready to be moved into its own separate build target. The foundation of the engine is [Cinder][6] which is a great library for creative coding that abstracts away a lot of the low level problems such as cross platform events and the ability to load a broad array of media formats for textures. It allows full access to low level open GL methods with convenient wrappers so that a game engine can be built on top of it. Game logic is written in Lua with wrappers to game engine functionality and scenes are loaded by deserializing Yaml scene files which are passed into the engine. This means the engine is completely separate from the actual game.

The targeted platforms are Windows and OSX as these are the platforms supported by cinder. iOS is also supported but is low priority. Currently there only a build project for XCode on OSX but the ability to use Windows is in the pipeline. The engine uses no platform dependent functionality so porting should not be a massive undertaking.

Current State
-------------
The game is still very premature with only some basic functionality implemented. If you really want to try it out you will need a Mac with Xcode as a cross platform build system isn't implemented yet. Simply check out the repository and the Xcode project should just run as I have included all dependencies in the repository and added relative search paths. 

![Screenshot of current state](https://raw.githubusercontent.com/NoxHarmonium/spacestationkeeper/master/README.png)

Credits
-------------
*Libraries*
- [MIT License][0]
    - [lua][1]
    - [luabind][2]
    - [yaml-cpp][3]
    - [astar-algorithm-cpp][4]

- [Modified BSD License][5]
    - [cinder][6]

- [Boost License][7]
    - [boost][8]


*Assets*
- [Multiple Authors]
    - Asteroid Tileset: [CC-BY-SA 3.0][9] / [GPL 3.0][10] [Source][11]
    


[0]: http://opensource.org/licenses/MIT/                    "Mit license summary"
[1]: http://www.lua.org/                                    "Lua website"
[2]: http://www.rasterbar.com/products/luabind.html         "LuaBind website"
[3]: https://code.google.com/p/yaml-cpp/                    "yaml-cpp Google Code page"
[4]: https://github.com/justinhj/astar-algorithm-cpp        "astar-algorithm-cpp GitHub page"
[5]: http://oss-watch.ac.uk/resources/modbsd                "Modified BSD License summary"
[6]: http://libcinder.org/                                  "Cinder website"
[7]: http://www.boost.org/users/license.html                "Boost license summary"
[8]: http://www.boost.org/                                  "Boost website"
[9]: http://creativecommons.org/licenses/by-sa/3.0/         "CC-BY-SA 3.0 summary"
[10]: http://www.gnu.org/licenses/gpl-3.0.html              "GPL 3.0 summary"
[11]: http://opengameart.org/content/tiled-terrains         "Asteroid tileset source link"


