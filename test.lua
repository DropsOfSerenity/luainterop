function saysomething()
  io.write("Yolo, from inside .saysomething in lua\n\n")
end

function square(n)
  io.write("Calling .square with argument: ")
  io.write(tostring(n))
  n = n * n
  io.write(", square = ")
  io.write(tostring(n))
  print(".")
  return(n)
end

function ChangeTable(inTable)
  local result = {num=1}
  for k,v in pairs(inTable) do
    result.num = result.num + 1
    result[tostring(k)] = string.upper(tostring(v))
  end

  return result
end

print("priming....")
