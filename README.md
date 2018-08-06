HaterMatic
==========

[![Hatermatic](https://cdn.sparkfun.com/r/500-500/assets/home_page_posts/1/4/2/1/Hater-Matic_CoinOperatedPrinter_Arduino.jpg)](https://cdn.sparkfun.com/assets/home_page_posts/1/4/2/1/Hater-Matic_CoinOperatedPrinter_Arduino.jpg)

The HaterMatic project is a coin-operated insult dispensing machine. It sells harsh language to you, with higher quality and more original insults coming from higher prices.

### The Hardware

The HaterMatic is powered by a SparkFun Arduino Pro Mini 5V, although any Arduino-compatible board can be made to work (or for that matter, most other microcontroller boards). The board receives coin-counting signals from our 6-denomination coin acceptor; the 3-denomination acceptor can be made to work by modifying the code to count output pulses instead of looking for serial data. The request for a receipt occurs when the user presses a big green button on the front of the machine, and it's printed out by our small thermal receipt printer. The whole affair is powered by two supplies: a 9V supply for the printer and a 12V supply for the Arduino and coin acceptor.

[Click this link](https://www.sparkfun.com/wish_lists/81471) to see a complete wish list of all the parts you'll need to make it. Obviously, depending on what you have in your parts bin, you may be able to eliminate some of these items.

### The Software

The firmware for the HaterMatic was written in Arduino 1.0.5, but it should compile and load under 1.5.3, as well. There are no special library requirements for it.

Documentation
--------------

* **[Hookup Guide](https://github.com/sparkfun/HaterMatic/wiki)** - For more information, please check the Wiki for this repository.
* **[SparkFun Live: Coin-operated Insult Generator - Hatermatic](https://www.sparkfun.com/news/1421)**
* **[Enginursday: The LoverMatic](https://www.sparkfun.com/news/2286)**
