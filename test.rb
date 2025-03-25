#! /bin/ruby

require 'optparse'

options = {fast: false, valgrind: false}
OptionParser.new do |opts|
  opts.on("-f", "--fast", "generate small tests and execute the program") {options[:fast] = true}
  opts.on("-v", "--valgrind", "enabled valgrind in tests") {options[:valgrind] = true} 
end.parse!

if(!options[:fast])
  TEST_NUMBER = 10 # numbers of tests
  MAX_NUMBER_OF_NUMBERS = 10000 # maximum of numbers that could be in 1 test
  MAX_NUMBER = 1000000 # maximum number in test
else
  TEST_NUMBER = 10 # numbers of tests
  MAX_NUMBER_OF_NUMBERS = 1000 # maximum of numbers that could be in 1 test
  MAX_NUMBER = 10000 # maximum number in test
end

if(options[:valgrind])
  VALGRIND = 1
else
  VALGRIND = 0
end

puts "Generating tests"
a = 1
while a <= TEST_NUMBER do
  file = File.open("./tests/test" + a.to_s + ".input", "w")
  
  number = rand(MAX_NUMBER_OF_NUMBERS)
  File.write("./tests/test" + a.to_s + ".input", number)
  File.write("./tests/test" + a.to_s + ".input", " ")
  while number > 0 do
    File.write("./tests/test" + a.to_s + ".input", rand(MAX_NUMBER), mode: "a")
    File.write("./tests/test" + a.to_s + ".input", " ", mode: "a")
    number -= 1
  end
  puts "Test ##{a} ready"
  a += 1
  file.close() 
end
puts "\n\nAll the tests ready. Starting the program\n\n"
system("make")
a = 1
all_tests_passed = true
is_test_passed = true
while a <= TEST_NUMBER do
  puts("----------TEST ##{a}--------------------")
  if(system("./a.out < ./tests/test#{a}.input") == 0)
    all_tests_passed = false
    is_test_passed = false
  end
  if(is_test_passed == true)
    puts("----------Test ##{a} passed!------------\n\n")
  else
    puts("----------Test ##{a} FAILED!------------\n\n")
  end
  is_test_passed = true
  a += 1
end
if(all_tests_passed == true)
  puts("All the tests completed succesfully!\n\n")
else
  puts("Some tests failed!\n\n")
end
