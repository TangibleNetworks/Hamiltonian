HAMILTONINAN
Espen Knoop

Game: finding Hamiltonian paths in networks.

3 states: current, visited, unvisited.  Press button on unvisited node adjacent to current node to move along.  To win, visit all the nodes.

Unvisited: pale blue?
Current: green
Visited: yellow
Nope: red
Win: all green.

Power on: go to unvisited mode.

Master sw: go into init() mode.  All go blue, until sw is pressed on one node.  This becomes the starting node, and the game begins.

Call/response:
  * Press switch: send a random number. If you get it back, you're the current node.  Current(): if you receive a number, you're visited.

Winning
 * If any input or yourself is NOT_WIN, output NOT_WIN.  Otherwise output WIN. If starting node receives WIN, output WON and go green.  If input is WON, set all outputs to WON and go green.

WIN = not connected = 0.0 (<0.02)
WON = 0.03: 0.02 < WON < 0.04.
NOT_WIN: > 0.98

Call/response: between 0.04 and 0.98.  N values.  More = better but less robust.

Init (not at startup, only when masterSw is pressed): Start by broadcasting WIN.  Press button -> broadcast NOT_WIN over network and start game.  Means: if you connect new node at this stage it will assume WIN.  So in WIN, if we receive NOT_WIN then go to unvisited().

But WIN and setup need to look different for most of the nodes.  Think it's acceptable that nodes connected during setup (which will rarely happen) are a different colour.

Transmit/receive: WIN, NOT_WIN, Query.
Need to store if you're starting node (set in setup).
States: init(), unvisited(), current(), visited(), win().

Can only go to WON after WIN.  So WON can be the same as "go".  And in the same way as before, if 

init()
  Enter if masterSw is pressed (at any point in the game).
  Wait, outputting 0. (so a new node will think WIN which is fine)
  If switch is pressed, you're the current() node.  Output 1.
  If you receive 1, pass it on.  You're unvisited().
  Short delay before moving on!
unvisited()
  Output NOT_WIN.  
  If switch is pressed, output random query.  If you get it back: green (immediately), current() (when released).
  If masterSw, init().
  Don't care about inputs.
current()
  If inputs are WIN, output WIN (or WON if starting node).  Otherwise output NOT_WIN.
  If inputs are WON, output WON, won().
  If any input receives a query, return it (the first query) on all outputs and become visited() after 0.1s.
  If masterSw, init().
visited()
  If masterSw, init().
  If inputs are WIN, output WIN (or WON if starting node).  Otherwise output NOT_WIN.
  If inputs are WON, output WON, won().  
won()
  If masterSw, init().
  



WINNING
Isn't working at the moment.
Because starting node never goes into winning mode.
One of them needs to make the first move!
 * If starting one sees WIN, he'll send out WON.  So next one can't send WIN until the end.  
 * Could consider the inputs that aren't backwards in the chain.
 * What happens if there's a loop? That's ok.  So current should check all the time 
 Keeps on turning in to 'who draws first'...

Do we need another state? Tricky.  

What about ignoring one of the inputs?  Know that one of the inputs is going down the path so will be OK.  

Winning = no more unvisited nodes.

OK.  Winning doesn't have to be global.  Can also be when there's nowhere to go i.e. end of the game.  So if none of the neighbours of the current node are high i.e. not visited, send WON signal.  If I get a WON while unvisited(), I go red (but pass on WON).

So states become:
Unvisited: 1.0 (>0.98)
Visited/not connected: 0.0 (<0.02)
WIN: 0.03 (<0.04, >0.02)
Current is also visited.
WIN can only be initiated by current node!














