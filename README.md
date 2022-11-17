# Advanced-Programming-Project
This project was made by Omer Bar and Shilo Padael in our second year of our Computer Science B.A.

<h2>How To Run?</h2>
<h4>For Linux:</h4>
<ol>
  <li>Download the zip file of the project, and exctract the zip.</li>
  <li>open terminal in the project folder.</li>
  <li>Run the following commands: (without the '$')</li>
  <pre><code>$ cmake -B build
$ cd build
$ make
$ ./runnable</code></pre>
</ol>

<h4>For Windows:</h4>
<ol>
  <li>Download the zip file of the project, and exctract the zip.</li>
  <li>open project with IDE.</li>
  <li>build the project from the IDE with the CMakeList.txt file.</li>
</ol>

<h3><i>----------Milestone 1: 24.11.2022 ----------</i></h3>
<h4>Creating different algorithem to calculate the distance between 2 vectors</h4>
<p>We implement it using an abstract class called Distance that implements 2 functions and another virtual function.
For each algorithem that inheritance the Distance class it should only implements the virtual function. In this project
we didnt implement a Vector class, We use the std vector class.</p>
<h4>How to calculate the distance?</h4>
<ol>
  <li>Creating an instance of the algorithm.</li>
  <li>Applying the operator () on the instance and saving the value.</li>
</ol>
<p>Let's calculate the Euclidean distance for example:</p> 
<pre><code>// creating the vectors
std::vector v1 = {1, 2, 3};
std::vector v2 = {3, 2, 1};
Euclidean euclidean; //creating instance of Euclidean algorithem.
double result = euclidean(v1, v2) // returning the distance between v1 and v2.
</code></pre>

<p>By using an abstract class we can make use of polymorphism</p>
<pre><code>Euclidean euclidean;
Distance* pDistance = &euclidean;
double result = (*pDistance)(v1, v2); // returning the distance between v1 and v2.
</code></pre>

<h4>How to add another distance algorithem?</h4>
<ol>
  <li>Creating a new class by the name of the algorithem inside folder calculate.</li>
  <li>Inheritance the Distance class (after including it).</li>
  <li>Override the virtual function in Distance class named: operator().</li>
</ol>

