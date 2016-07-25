# Emulation-Platform

To run locally:

User:
```
g++ -o user User.cpp User-main.cpp
./user localhost userportno
```

Controller(ctrlport = userport+1): 
```
g++ -o ctrl Controller.cpp
./ctrl ctrlportno
```

Platform:
```
g++ -o platform EmulationPlatform.cpp EmulationScheduler.cpp Pattern.cpp QualityEvaluator.cpp
./platform localhost userportno trace.txt
```

