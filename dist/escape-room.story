Success
Paid
Key
Light
Searched
Drawer
Start
Bathroom
Left

Lobby
|lobby-bg
!Paid|lobby-door-closed
Success|lobby-door-closed
!Paid|lobby-gm-counter
Start|lobby-gm-counter
Bathroom|lobby-gm-counter
Paid,!Start,!Bathroom|lobby-gm-door
Paid,!Success|lobby-door-open

!Success,Bathroom|The game-master lets you out of the room.
!Success,Bathroom|You head to the bathroom and return. The
!Success,Bathroom|game-master is no longer waiting for you
!Success,Bathroom|at the door.
|You are standing in the lobby
|of a real-life escape game room.
!Paid|The game-master asks for payment.
Paid,!Start|The game-master beckons you to enter.
Success|The game-master is miffed that you
Success|finished so quickly, taking the key
Success|from you in a huff.

!Paid|Paid|Lobby|Pay
Paid,!Start|Start|Room|Enter the room!
!Success,Bathroom|!Bathroom|Room|Enter the room and lock the door.
|Left|Leave|Leave

Room
|room-bg
Light|room-light
Drawer|room-drawer
Light,Drawer,!Key|room-key

|You are in the room. The game-master
|has locked the door.
!Searched|There is a table.
Searched|There is a table, drawer, and a switch
Searched|on the wall.
!Light,Drawer|The drawer is open, but it's hard to see
!Light,Drawer|inside it.
Light,!Drawer|The lights are on.
Drawer,Light,!Key|Light floods the drawer. A twinkle in the
Drawer,Light,!Key|drawer catches your eye. A key!
Drawer,Light,Key|The drawer is very empty.

!Searched|Searched|Room|Examine the room.
Searched,!Drawer|Drawer|Room|Open the drawer.
Drawer|!Drawer|Room|Close the drawer.
Searched,!Light|Light|Room|Flip the switch.
Searched,Light|!Light|Room|Flip the switch.
Drawer,Light,!Key|Key|Room|Take the key.
Key,Drawer|!Key|Room|Put the key back.
Key|Success|Lobby|Use the key to open the door.
!Bathroom|Bathroom|Lobby|Use the bathroom.

Leave
|lobby-bg
!Bathroom|lobby-door-closed
!Success|lobby-gm-counter
Bathroom|lobby-door-open

!Paid|It's way too expensive. You go home
!Paid|instead.
Paid,!Start|You just have way too much cash
Paid,!Start|burn, so you decide to make the
Paid,!Start|game-master's day and go home.
Bathroom|You decide that you have had enough
Bathroom|and just leave without finishing.
Bathroom,Key|When you get home, you realize the
Bathroom,Key|key is still in your pocket. Oops!
Success|As you leave, the game-master closes
Success|for the day to try to increase the
Success|the difficulty of the room.

||Leave|The End