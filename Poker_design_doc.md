# Elements of the design

### Generic Cards / Player Hand classes seperated from any card game logic

### Cards are the core element, usable for any card game (Card library)

### concept of "player Hand", deck and as an ownership container for the set of cards which a player has (PlayerHand library)

stacks / double ended queues for ordered drawing and card disposal

### Design decision: should the cards be a finite set of objects allocated to the heap at initialization? 

Pro: stable, clear ownership and provably no duplication due to unique pointer movement
Contra: non contiguous memory in the player hands will lead to slower sorting or comparison operations
Neutral: such games will have very low performance and memory requirements relative to the hardware, therefore either option will be fine

### Seperation of the player Hand from the Card Game and score evaluation
Pro: Card Game logic is specific to each game and can be adapted to 5 card poker, texas holdem or other types of poker



