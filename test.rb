#! /bin/ruby
# TODO valgrind
Random.new_seed

TEST_NUMBER = 10

puts "Generating tests"
a = 1
while a <= TEST_NUMBER do
  file = File.open("./tests/test" + a.to_s + ".input", "w")
  
  number = srand % 10000
  File.write("./tests/test" + a.to_s + ".input", number)
  File.write("./tests/test" + a.to_s + ".input", " ")
  while number > 0 do
    File.write("./tests/test" + a.to_s + ".input", srand % 1000000, mode: "a")
    File.write("./tests/test" + a.to_s + ".input", " ", mode: "a")
    number -= 1
  end
  puts "Test ##{a} ready"
  a += 1
  file.close() 
end
puts "All the tests ready. Starting the program\n"

a = 1
all_tests_passed = true
is_test_passed = true
while a <= TEST_NUMBER do
  if(system("./a.out < ./tests/test#{a}.input") == false)
    all_tests_passed = false
    is_test_passed = false
  end
  if(is_test_passed == true)
    puts("Test ##{a} passed!")
  else
    puts("Test ##{a} FAILED!")
  end
  is_test_passed = true
  a += 1
end
if(all_tests_passed == true)
  puts("All the tests completed succesfully!")
else
  puts("Some tests failed!")
end
