# LLM Usage Explained

I used an llm primarily to help with topic research and tedious code generation.

For example, I used claude to help me determine what filtering technique would be best for Q1.
I described to it the qualitative features of the data I had observed (like jittering and
asymmetric downward dropoffs in the altimeter reading) and it gave a Kalman filter and EMA filter
as options.

Another example is in the notebook for q1. I originally graphed the gps and altimeter values
using a simple pyplot but I found that one of the altimeter data streams would cover the other.
So I asked claude to make an interactive graph that would let me toggle certain columns on or off.
