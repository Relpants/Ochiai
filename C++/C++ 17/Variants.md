Variants

# Variants

## Member functions
- Constructor
`std::variant<int,std::string> a{2017},b{"illidan"};`

- Deconstructor
- operator=
	
	- `a = b;` 
		- a: "illidan"
		- b: "illidan"
	
	- `a = std::move(b);`
		- a = "illidan"
		- b = ""
	

## Non-member functions
- ***visit***
- holds_alternative
- std::get
- get_if


## Example
`std::variant<int, float> v;` - creates a variant that hold either an int or float

