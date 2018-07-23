# Kiln
A 2d game engine built on top of SDL2 using C++. (currently a work in progress).

## What I have so far.
* Asset Manager
  * Load images, music, sound, and fonts.
  * Unloads assets and frees the memory.
  * Assets are loaded into a map and can be fetched with a key supplied when loading.
* Window Manager
  * So far this just stores references to the renderer, window, and resolution.
  * I plan on using this to handle resolution changes.
* Input Manager
  * Polls the event queue. Stores the last event, the last click event, and the cursor position.
  * I plan on adding quite a bit more functionality such as click and drag, multi-click, held keys/buttons etc.
* State Machine
  * This contains a stack which stores states.
  * The state at the top is considered the active state.
  * Manages state init, cleanup, pause, and resume.
  * Manages adding/removing/replaces states in the stack.
  
## Building
Currently only tested in Linux.
1. Ensure you have SDL2, SDL_image, SDL_ttf, and SDL_mixer. (these libs will be included in the future).
1. Clone and cd into cloned dir.
1. $ cmake .
1. $ make
1. $ ./Kiln
