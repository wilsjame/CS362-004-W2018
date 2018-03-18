import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) 
   {

      super(testName);
      
   }

   
   
   public void testManualTest()
   {
	   
	   // Create new UrlValidator class instance
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	     
	   // Verify the instance is working
	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("http://www.google.com/"));
	   
	   /*
	   if (urlVal.isValid("http://www.google.com/")) {
	          System.out.println("url is valid");
	       } else {
	          System.out.println("url is invalid");
	       }
	    */
   }
   
   public void testRandomTest()
   {
	   
	   // Create new UrlValidator class instance
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	     
	   // Verify the instance is working
	   assertTrue(urlVal.isValid("http://www.myspace.com"));
	   assertTrue(urlVal.isValid("http://www.myspace.com/"));
	    
	   /*
	   if (urlVal.isValid("http://www.myspace.com/")) {
	          System.out.println("url is valid");
	       } else {
	          System.out.println("url is invalid");
	       }
	   */
	   
	   System.out.println("---Random Tester---");
	   
	   /*---------------------------------------------*/
	   int bugsFound = 0;
	   int size = 25;    /* number of random tests */
	   int bug_itr = 0;

	    /* Prepare valid url pieces */
	    String[] schemes_valid = {"h3tp://", "http://", ""};
	    String[] authority_valid = {"www.myspace.com", "myspace.com"};
	    String[] port_valid = {":80", ":300", ":3000"};
	    String[] path_valid = {"/", "/test"};
	    String[] options_valid = {" ", "/test", "/test/test"};
	    String[] queries_valid = {" ", "?action=view"};
	    
	    /* Create array to hold buggy urls */ 
	    String[] buggyUrls = new String[size];

	    /* Create a random url out of the valid url pieces.
	     * Loop through 10 times
	     */
	    for(int i = 0; i < size; i++) {
	      int scheme_random = (int) (Math.random() * 2);
	      int authority_random = (int) (Math.random() * 2);
	      int port_random = (int) (Math.random() * 3);
	      int path_random = (int) (Math.random() * 2);
	      int options_random = (int) (Math.random() * 3);
	      int queries_random = (int) (Math.random() *2);

	      /* Piece together the randomly generated url parts in the correct format. */
	      String test_url = schemes_valid[scheme_random] + authority_valid[authority_random] + port_valid[port_random] + path_valid[path_random] + queries_valid[queries_random];
	      UrlValidator test_validator = new UrlValidator();

	      /* Test url using the UrlValidator */ 
	      boolean is_valid = test_validator.isValid(test_url);

	      /* If invalid, store for later and increment bugs found */ 
	      if(is_valid == false) {
	        buggyUrls[bug_itr] = test_url;
	        bug_itr++;
	        bugsFound++;
	      }
	      
	    }
	    
	    // print results
	    System.out.println("Bugs found: " + bugsFound);
	    
	    // Uncomment to show invalid urls found
	    System.out.println("\nBad URLs:");
	    for (int j = 0; j < buggyUrls.length; j++) {
	      if(buggyUrls[j] != null){
	    	System.out.println(buggyUrls[j]);
	      }
	} 
	    /*---------------------------------------------*/ 
	   
   }
   
    
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition()
   {
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
