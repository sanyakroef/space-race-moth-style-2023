# Space Race, Moth Style
A space racing game with gradually increasing physics bugs.
Rendered using ray-marching and ANSI.

Potential Epilepsy warning!!! for the bugs (in that case disable them by adding "-no_bug" to the command line arguments).

# How to play
## running the game
1. compile the program
2. make sure the terminal is configured to properly feed mouse events. (This can generally be achieved by running the program using `TERM=xterm-1003 ./spel`)
3. make the font size of your terminal tiny. (This can generally be achieved by repeatedly pressing ctrl+`-`) (Warning: don't make it to small though, as the mouse will otherwise be constrained to a portion of the screen)
4. run the program

You can choice you spaceship by adding "-s" and then the id of the spaceship.
0. a paper clip based space ship
1. a paper clip based space probe
2. the Hungat
3. the damaged Hungat
4. a warp drive test vehicle
5. a escape pod
These are ordered in order of easiest to hardest (according to me).

You can specify the target frame-rate using "-f", though the scores might not be exactly comparable to that achieved with other frame-rates.

## controls
You use the levers on the bottom of your screen to control the thrusters on you spaceship.
You can quite by pressing "q".

You goal is to collect all goals (green glowing celestial objects) as fast as possible.
Though you might want to start trying to collect as many as you can.
Every time you collect a goal the universe glitches until you manage to get away. (unless you disabled this feature)
