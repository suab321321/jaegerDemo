# jaegerDemo

1.Clone the repo
2.Go inside the repo.
3. open terminal now run `g++ -std=c++1z test.cpp` -L /usr/local/lib/libyaml-cpp.a -ljaegertracing -lyaml-cpp`
4.run the jaeger server (I have used jaeger-all-in-one) you can find about them 
here https://www.jaegertracing.io/docs/1.17/getting-started/

5. run a.out
6. open browser goto to http://localhost:16686
7.inside service select the name 'example-service-2'
8.you will be able to see your individual spans by clicking on main tracer.

