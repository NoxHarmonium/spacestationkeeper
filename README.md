Space Station Keeper
====================

Overview
--------
Working title for a game which will basically be a clone of Dungeon Keeper but on an asteroid. I am working on it mostly to learn c++/graphics programming while traveling (most of the code is written on 10 hour bus trips or in a hostel dorm). I've actually written quite a bit of code which means that I'm either a terrible traveler or an efficient coder. I hope the latter. It is something that might not come fully into fruition but I hope to learn a lot in the process. 

I'm using a library called Cinder which is a really solid foundation for a game engine as it handles things like loading PNG files as textures and wraps complex openGL functions in neat wrappers (although you still need to know what it is doing under the hood). 

Libraries Used
-------------
cinder
libyaml-cpp
boost
cairo?
lua?

Current State
-------------
Asset management is implemented and a basic scene graph and render pipeline is implemented. Next step is to introduce jobs. For example currently you can select blocks to mine, the next step is adding a job that mines the blocks and turns them into corridor tiles over time.

Game play
--------
Ideally the formula I am aiming for Dungeon Keeper II + Caesar III + FTL: Faster than light. The player starts off with a big grid of asteroid rock and a docking bay. The player can select the rock they want to mine and robots will mine the selected rock and build empty rooms/corridors. Base facilities can be built which attract certain kinds of workers. For example, miners don't mind sleeping in cheap dormitories where as the high level engineers running base facilities want something nicer. Each base facility has a base level requirement of work but will operate a higher efficiency if extra optional staff are available. For example a fungus farm may produce adequate quality fungus with 5 farmers, but an optional botanist can help the quality improve significantly. Alas you will need a more desirable base to attract these kinds of people. Worker's experience toiling in base facilities accumulate and add to the quality of the product. You have a warehouse where cargo bots deliver the output of your base facilities and also imported deliveries from the cargo bay. Its also where resources required for your base facilities are drawn from (i.e. fuel for the reactor). You can choose the amount of surplus you want to keep in your warehouse, anything over the surplus is exported and imports can supplement your stocks when there is a shortage. When your base becomes successful, other asteroids start to notice and will try to sabotage your base. You can build doors and traps to ensnare wanderers and security centers to investigate worker corruption. You are also able to research technologies to make your base work more efficiently. You are able to fit into the economy any way you like. For example you could start with an asteroid that is rich in metal ores and simply export them, or you could import ores and refine them and export the refined metal. You could even master the whole resource chain and mine, smelt and construct valuable goods all on the same asteroid and would be only one facet of the economy.

I am working out the list of base facilities as I go along but I have some examples:
-Reactor - Provides essential power to the base. Every base facility uses some amount of power, some more than others. The reactor requires a constant supply of fuel to keep going. If there is a power shortage due to over extending the base or something happening to a power plant you can selectively disable parts of the base.
-Dormitory - Provides a cheap place to stay for workers.
-Cafeteria - Distributes food to the workers. Better food attracts better workers. 
-Fungus Farm - Creates the base food source that can be used to create more interesting food. 
-Mine - Extracts a constant but limited supply of a metal ore from the asteroid (you can uncover veins while hollowing the asteroid). 
-Refinery - Takes the ore from the mines and refines it into something more useful such as building supplies.

Asset Credits
-------------
Asteroid Tile set: http://opengameart.org/content/tiled-terrains
