# EcoShower
Using Arduino Uno, DS18B20 temperature sensor and a relay

Background:
My 13 year old daughter does love a good shower. 
She REALLY loves one, up to the point where she has been spending up to two hours in the bathroom. 
We suspect that she has been turning the bathroom into her own personal sauna.
The result of which is that the rest of the household are having to have very quick, very cold showers unless we keep the boiler on all evening.
We've recently had a water meter installed and our bill has trippled, not to mention our gas bill has rocketed.
Now, you can't reason with a teenage girl and expect a happy outcome where washing is concerned, so another solution was required, and I do like a good problem.

Our shower requires a pump for it to produce enough pressure to be useable. 
The pump is housed by the hot water tank in the airing cupboard in my sons bedroom. 
I had recently bought my son an Arduino and a pile of sensors to play about with. All this was fun, but we needed a worthy project to put it all to good use.

After a week of consecutive cold showers, I had a Eureka moment!
What if we were to strap a temperature sensor to the hot pipe and use it to trigger a timer on the Arudino when it reached say 40 degrees (centigrade).
Then once the timer has run its course, it triggered a relay that cut the power to the shower pump.
The relay remains switched until the hot water pipe falls below the threshold temperature, at which time the process repeats itself.
The beautiful simplicity is that the off-time is wholely dependent on the cooling of the pipe. 
The relay is only activated for the period when the timer has finished, and the hot pipe is above the threshold temperature. 
To bypass the "Eco-Shower", as we like to call it can be done by cutting the power to the Arduino.

There have been a few additions we have made to it since the proof of concept. 
It now has two pots, one to set the threshold temperature, and the second to set the timer period (or the amount of time the shower runs for before it turns into a pathetic dribble).
There's also a green led that comes on when the temperature sensor has reached the threshold and the timer is running, and a red one when the relay cuts the power to the pump.


We've had this running for about three months now and had a great deal of fun with it.
My daughter gets out of the shower without a word said after 15 minutes, like clockwork every day, and we all have hot showers. 
I am anticipating a marked drop in our gas and water bills.
I still have the problem of trying to get my son in the shower for more than a minute, but I guess that's going to require a different approach.
