WontLeave
DunesVisit
TookStone
OasisVisit
AddedStone
HillVisit
Finished

Dunes
|dunes-bg
!Finished|dunes-traveller
!Finished|dunes-ship

!DunesVisit|The landing is turbulent.
!DunesVisit|As the sand settles, I see there is
!DunesVisit|nobody here to meet me.
!Finished,DunesVisit|There is still nobody here to meet me.
Finished|You leave, your mission accomplished.
| 
!AddedStone,WontLeave|Something remains to accomplish. I won't leave.

AddedStone|Finished|Dunes|Leave
!AddedStone|WontLeave|Dunes|Leave
|DunesVisit|Oasis|Walk East
|DunesVisit|Hill|Walk West

Oasis
|oasis-bg
!TookStone|oasis-missing
|oasis-traveller

!OasisVisit|I search east, walking in ever-greater
!OasisVisit|circles. Just over the next dune, I find
!OasisVisit|an oasis.
OasisVisit|The oasis sparkles in the sunlight.
| 
!TookStone|Glinting in the glass-clear water is a
!TookStone|single blue gemstone.
TookStone,!AddedStone|The stone fits snugly in my pocket.

!TookStone|TookStone|Oasis|Take Stone
|OasisVisit|Dunes|Return to the Ship

Hill
|hill-bg
AddedStone|hill-missing
|hill-traveller

!HillVisit|I set off confidently to the west.
!HillVisit|At the top of the third dune, a circle
!HillVisit|of stones surrounds a shallow depression
!HillVisit|in the ground.
| 
!AddedStone|The circle of stones stands expectantly.
AddedStone|I add the blue stone to the circle.
AddedStone|Something trembles deep underground.

TookStone,!AddedStone|AddedStone|Hill|Add Blue Stone
|HillVisit|Dunes|Return to the Ship