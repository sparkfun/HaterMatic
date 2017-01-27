/******************************************************************************
loveStrings.h
Insults for the "LoverMatic" project
Mike Hord @ SparkFun Electronics
27 Jan 2017
https://github.com/sparkfun/HaterMatic

This code uses SparkFun's 6-value coin accecptor (COM-11636) and thermal
printer (COM-10438) to allow people to pay to have a lovely complement
directed at them. This file contains the actual complements.

Resources:
SoftwareSerial library
avr/pgmspace.h

Development environment specifics:
Developed in Arduino 1.8.1
Developed on a SparkFun Arduino Pro Mini 5V/16MHz (DEV-11113)

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/
// These define the number of complement strings for each tier. This limits the
//  number of phrases that can be selected from; don't forget to increment (or
//  decrement!) this value if you add (or remove) complements.

#define NUM_V 4  // Number of "value" level complements.

// While this "double-define" thing, where we declare a variable, then declare
//  an array with those variables in it, looks hokey, it's how you *need* to
//  write strings into flash memory. If the strings were simply inlined into
//  the meta-array, you'd end up with an array of pointers to RAM locations
//  and only the pointers would be stored in flash; the strings would still be
//  in RAM, clogging up your tubes.
const char vs1[] PROGMEM = "YOU ROCK";
const char vs2[] PROGMEM = "CUTE STUFF";
const char vs3[] PROGMEM = "BE MINE";
const char vs4[] PROGMEM = "MAYBE TONIGHT";

const char* const valueStringList[] PROGMEM=
{
  vs1,
  vs2,
  vs3,
  vs4
};

#define NUM_Q 8  // Number of "quality" complements

const char qs1[] PROGMEM = "I love the way your face is.";
const char qs2[] PROGMEM = "Your hair is beautiful today.";
const char qs3[] PROGMEM = "I love that outfit!";
const char qs4[] PROGMEM = "You make me smile.";
const char qs5[] PROGMEM = "You have a great laugh.";
const char qs6[] PROGMEM = "I like you a lot.";
const char qs7[] PROGMEM = "You have a good heart.";
const char qs8[] PROGMEM = "You are awesome.";

const char* const  qualityStringList[] PROGMEM= 
{
  qs1,
  qs2,
  qs3,
  qs4,
  qs5,
  qs6,
  qs7,
  qs8
};

#define NUM_L 17  // Number of "luxury" phrases, for those who have everything.

const char ls1[] PROGMEM = "You take my breath away.";
const char ls2[] PROGMEM = "I love you more than the moon and stars.";
const char ls3[] PROGMEM = "You're the best part of my day.";
const char ls4[] PROGMEM = "Love you, puppycat!";
const char ls5[] PROGMEM = "I\'ll take care of dinner tonight.";
const char ls6[] PROGMEM = "I love you like Kanye loves Kanye.";
const char ls7[] PROGMEM = "I love you like grilled cheese loves tomato soup.";
const char ls8[] PROGMEM = "You are cuter than a koala bear riding a red panda.";
const char ls9[] PROGMEM = "I missed your face.";
const char ls10[] PROGMEM = "You are my favorite person.";
const char ls11[] PROGMEM = "The sun could never compare to the love your heart shines.";
const char ls12[] PROGMEM = "You make my heart smile.";
const char ls13[] PROGMEM = "There is nowhere I\'d rather be than with you.";
const char ls14[] PROGMEM = "I absolutely love who you are.";
const char ls15[] PROGMEM = "You take my heart with you when you go.";
const char ls16[] PROGMEM = "My heart beats for you.";
const char ls17[] PROGMEM = "Seeing you makes any day better.";

const char* const  luxuryStringList[] PROGMEM =
{
  ls1,
  ls2,
  ls3,
  ls4,
  ls5,
  ls6,
  ls7,
  ls8,
  ls9,
  ls10,
  ls11,
  ls12,
  ls13,
  ls14,
  ls15,
  ls16,
  ls17
};

/*
I'm leaving this section in, but commented, because it's a useful example of
what *not* to do. The way I've done things here, you end up with an array of
pointers to strings stored in SRAM stored in flash, *not* an array of strings
stored in flash. See above for the correct, albeit clumsy, way to do it.

#define NUM_V 4  // Number of "value" level insults.
PROGMEM const prog_char *valueStringList[] =
{
  "Doodoo breath!",
  "Poopy head!",
  "Butthead!",
  "Dummy."
};

#define NUM_Q 8  // Number of "quality" insults
PROGMEM const prog_char *qualityStringList[] = 
{
  "Stuck up, half-witted, scruffy looking nerf-herder!",
  "Your mother was a hamster!",
  "Your father smelt of elderberries!",
  "Does Barry Manilow know you raid his wardrobe?",
  "Warthog faced buffoon!",
  "You're just dumber than a bag of hammers.",
  "Were you always this stupid, or did you take lessons?",
  "You are a neo-maxi zoom dweebie."
};

#define NUM_L 8  // Number of "luxury" insults, for those who have everything.
PROGMEM const prog_char *luxuryStringList[] =
{
  "It may be that the purpose of your life is solely to be a warning to others.",
  "If we throw you a going away party, will you?",
  "It must be hard being brilliant with no way to prove it.",
  "You are not a good person. You know that, right?",
  "Here are the test results: You are a horrible person. I'm serious, that's what it says: \"A horrible person.\" We weren't even testing for that.",
  "You\'re not just a regular moron. You\'re the product of the greatest minds of a generation working together with the express purpose of building the *dumbest* moron who ever lived.",
  "I advise you to have the top of your head taken off, the contents removed, and allow some sensible person to poo in it.",
  "You\'d bring a fork to an all-you-can-eat soup bar.",
  "Some people spread joy wherever they go. You spread joy whenever you go.",
  "Just when I think you’ve said the stupidest thing ever, you keep talking.",
  "You're morally reprehensible, vulgar, insensitive, selfish, stupid, you have no taste, a lousy sense of humour and you smell.",
  "You are a sad, strange little person, and you have my pity.",
  "Tell me, did you dress like that on purpose?",
  "You make me feel like a better person.",
  "I\'ve trained dogs with more personality than you.",
  "If all the village idiots left their villages and formed their own village, in that village, YOU would be the village idiot.",
  "The YouTube comments about you are all true."
};
*/

