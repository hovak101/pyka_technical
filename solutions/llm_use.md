# LLM Usage Explained

I used an LLM primarily to help with topic research and tedious code generation.

For example, I used Claude to help me determine what filtering technique would be best for Q1. I described to it the qualitative features of the data I had observed (like jittering and asymmetric downward dropoffs in the altimeter reading), and it gave a Kalman filter and an EMA filter as options.

Another example is in the notebook for Q1. I originally graphed the GPS and altimeter values using a simple pyplot, but I found that one of the altimeter data streams would cover the other. So I asked Claude to make an interactive graph that would let me toggle certain columns on or off.
