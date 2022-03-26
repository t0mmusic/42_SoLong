# 42_SoLong
A very basic game made in c.
## Purpose
The goal of this project is to render images in a window and update those images with user inputs. In order to demonstrate this, we make a simple game.
The game consists of moving a player around to collect items and then reach an exit. Each of these are represented by a single character. <br>
- P is the player
- C is the collectable item
- E is the exit
- 0 is an empty space the player can move to
- 1 is a wall the player cannot move past

A map is made using this criteria and stored in a file with the extension '.ber', which is then imported into the program. <br>
An example of a valid map would be:<br><br>
11111111111<br>
1C00001E001<br>
10P01001001<br>
10001000001<br>
11111111111<br><br>
The map must be rectangular to be valid.
## Status
Ongoing. Game logic has been completed and image rendering is working, but a few behind the scenes improvements must be made.
