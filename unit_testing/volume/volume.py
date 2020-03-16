# Encontrar el volumen de una esfera
# V = (4/3) *  pi * (r**3)

from math import pi

def volume(radius):
    if type(radius) not in [int,float]:
	    raise TypeError("E. {ttype} not valid ...".format(ttype = type(radius)))
    if radius < 0:
	    raise ValueError("Not negative can be used ...")
		
    return (4/3) * pi * (radius**3)

# raddi = [0, 1, 2, 3.0, -3, True, 3+2j, "radio"]
# message = "Given a Radius of {radius} the vol is {volume}."

# for r in raddi:
    # V = volume(r)
    # print(message.format(radius=r,volume=V))

