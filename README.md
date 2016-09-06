# Breakout
A polished clone of the classic Atari game Breakout

## Overview
This game is being developed for several reasons:
* Breakout is a fun game
* I can use it as a test bed for the underlying engine which is also being developed alongside the game
* I can use this as an example of my coding skills and a complete project which I developed
* This is my excuse to learn new skills in C++ 

## Design Goals
Provide a version of Breakout which is:
* Clean
* Simple
* Polished

Since this is also intended to help with the development of the engine, that engine should also include (in no particular order)
* A simple way to create new game entities
* A simple way to import new assets
* An event system to broadcasting events from one object to other subscribing objects
* A simple menu creation system including
	* Labels
	* Buttons
	* Sliders
	* Checkboxes
	* Drop Down Boxes
* Basic Options such as
	* Volume Controls
	* Screen Resolution
	* Fullscreen Toggle
* The ability to load and store options in between runs of the game
* A simple to use collision system
* A generic way to add state machines to game entities
* A generic way to add basic animations to game entities (RGBA fades, flashes, etc.)
* A system capable of playing sprite sheet based animations
* A generic way to add sounds to game entities
* (Possibly) a basic AI system 
	* I want to use this to make the game play itself in the background of the main menu simply for effect

## Final Thoughts
Many of the stated design goals have already been met and this is currently in a state in which is is playable.  It is still however under development and since it is not intended to every really "ship", it may see varied amounts of active development time.