# not-std

## What?
This is kind of a "code dump" repository to begin with. Upon trying to read and understand some of the 
standard library implementation, I couldn't stop myself from thinking about possible alternative (not
necessarily btter) ways to implement the same, or similar features, and with some toy code also came 
the feeling of not wanting to lose some of the fun results here, thus the creation of this repository.

## But, what?
At this time, stuff here are mostly related to some type-trait-y template metaprogramming toy programs, 
starting with integral constants and is_same. Currently the header is simply a single file, and a test 
`.cpp` file which uses static assertion to check behavior of the type traits. 

## Hmm
- Is anything here standard compliant?
  - Just like the name indicates, there's no guarantee anything is standard compliant. For instance the `integral_constant`, is not. 
  - Additionally, some stuff that are not, and likely will not ever be in the standard, may still be a fun excercise and are in fact added here.
	- For example extending `remove_all_extent` to handle `std::array` is likely not a very useful feature, yet it was somewhat fun to write, so here it is
- Some of the stuff here seems exactly the same as the common implementation, and you call this "alternative (not
necessarily btter) ways"? 
  - I wouldn' considere myself creative enough to the point of finding differnt implementations all the time, so I do admit defeat here
  - Besides, for some stuff there pretty much is no other way that is really significantly different. 
	- Say for example, it probably would be pretty difficult to really find a fundamentally different way to define `is_same_v`
  - By the end of the day the primary goal of having this repository is to practice, improve my understanding in STL, and get better at templates in general, so anything goes. 
- Is anything here really useful?
  - Nope