## Sirène


Weapons: 

The mermaid has 4 weapons. 

1. Trident. The first weapon. You fire 1 trident per button press with a delay allowing only 2 tridents on screen at once. Moves moderately fast, does moderate damage (2). Trident is destroyed when it makes contact with an enemy or is offscreen.

2. Bubble. The second weapon. The rapid fire weapon of the game. You fire a constant stream of bubbles by holding down the button. A quicker delay allowing 3 on screen at once. Moves fast does less damage (1). Bubble is destroyed when it makes contact with an enemy or is offscreen. Visually has a trail of tiny bubbles behind it. 

3. 3 Way Shells. The 3rd weapon of the game. You fire 3 shells (one diagonally up, one straight, one diagonally down) per button press with a delay allowing 2 sets 3 shells on screen at once. Moves moderately fast, each shell does less damage (1). Shells are destroyed when they make contact with an enemy or is offscreen.

4. Magic. The last weapon of the game. You can hold down the button to charge the magic. You can only fire one magic blast on screen at a time. Holding down the charge increases the damage. Magic blast travels through enemies but is destroyed when offscreen. Visually has a trail of magic behind it.


## WEAPONS LIST
| **SPRITE** | **SIZE** | **FRAMES** | **AMOUNT** | **DAMAGE** | **SPEED** | **LIFETIME** |
| ---        | ---      | ---        | ---       | ---             | ---             | ---             |
| **Trident** | 16x8 | 1 | 2 | -2 HP | 2 | 1 HIT |
| **Bubble** | 8x8 | 1 | 3 | -1 HP | 3 | 1 HIT |
| **3 Shells** | 8x8 | 1 | 2x3 | -1 HP | 2 | 1 HIT |
| **Magic** | 8x8 | 4 | 1 | -3 HP | 1 | CONTINUE HIT |

HUD

upper left corner LIFE, upper right corner POINTS

The remaining LIFE is displayed with 3 hearts. When the game starts, the mermaid has 3 full hearts. Everytime the mermaid is hit, she loses a heart (displayed with an empty heart). When you lose all 3 hearts, it's GAME OVER. When this happens GAME OVER screen is displayed with your current HIGHSCORE and when you press a button, you go back to the title screen. 

There's 7 digits displayed for the points. When the game starts, you have 0 000 000 points. Destroying enemies and collecting items can give you points. 

At the start of every level there's a quick message displaying what stage you're at. 


## ENEMIES
| **SPRITE** | **SIZE** | **FRAMES** | **NAME** | **HP** | **POINTS** | **MAX AMOUNT** |
| ---        | ---      | ---        | ---      | ---    | ---        | ---           |
| **Small Fish** | 8x8 | 4 | enemyFishy | 2 HP |   |   |
| **Big Fish** | 16x16 | 4 | enemyFish | 4 HP |   |   |
| **Eel** | 32x8 | 4 | enemyEel | 4 HP |   |   |
| **Jellyfish** | 16x16 | 5 | enemyJellyfish | 2 HP |  |    |
| **Octopus** | 16x16 | 4 | enemyOctopus | 4 HP |  |    |

Behaviors

Small Fish:
Swims offscreen from right to left. Small and weak, usually they swim in packs. 
Nice to have depending on how difficult it is:
1. have a variant that swims faster
2. have the ability to swim in a path other than a straight line: arc, sinewave. This might not be necessary but good to bring it up to consider it

Big Fish:
Same behavior as small fish, but a larger target with higher HP. 

Eel:
Swims in a straight line from offscreen. At a fixed interval will shoot a zap projectile at the mermaid. 

Jellyfish:
Swims in a stop and go pattern from the bottom of the screen upwards. 

Octopus: 
Swims offscreen from right to left. At a fixed interval shoots a bullet (meant to be ink) at the mermaid. 
1. If variable swimming patterns are possible, would be nice to apply them to the octopus as well. 

