/** 
 * FlashSort.java - integer version  
 * Translation of Karl-Dietrich Neubert's algorithm into Java
 * by Rosanne Zhang  
 * at www.webappcabaret.com/javachina 
 *
 * Code slightly modified by Erhan Tezcan
 */
   
class FlashSort {
  static int   n;
  static int   m;
  static int[] a;
  static int[] l;
  
  /**
    * constructor 
    * @param size of the array to be sorted
    */ 
  public static void flashSort(int size) {
    n = size;
 
    generateRandomArray(); 
    long start = System.currentTimeMillis();
    partialFlashSort();
    long mid = System.currentTimeMillis();
    insertionSort();
    long end = System.currentTimeMillis();
 
    // print the time result 
    System.out.println("Partial flash sort time     : " + (mid - start) );
    System.out.println("Straight insertion sort time: " + (end - mid) );
  }
 
  /**
    * Entry point
    */ 
  public static void main(String[] args) {
    int size = 0; 
    if (args.length == 0) {
      usage();
      System.exit(1);
    }
    try {
      size = Integer.parseInt(args[0]); 
    } catch (NumberFormatException nfe) {
      usage();
      System.exit(1);
    }
    FlashSort.flashSort(size);
  } 
 
  /**
    * Print usage
    */ 
  private static void usage() {
    System.out.println();
    System.out.println("Usage: java FlashSort n ");
    System.out.println("       n is size of array to sort");
  }
  
  /**
    * Generate the random array
    */ 
  private static void generateRandomArray() {
    a = new int[n];
    for (int i=0; i < n; i++) {
      a[i] = (int)(Math.random() * 5 * n);
    } 
    //printArray(a); 
    m = n/20; 
    /** 
    *  if (m < 30) m = 30; 
    */ 
    l = new int[m];   
  }
 
  /**
  * Partial flash sort
  */ 
  private static void partialFlashSort() {
    int i = 0, j = 0, k = 0;
     
    /***** CLASS FORMATION ****/
    int anmin = a[0];
    int nmax  = 0; 
    for (i=1; i < n; i++) {
      if (a[i] < anmin) anmin=a[i];
      if (a[i] > a[nmax]) nmax=i;            
    } 
    if (anmin == a[nmax]) return;
 
    double c1 = ((double)m - 1)/(a[nmax] - anmin); 
    for (i=0; i < n; i++) {
      k=(int)(c1*(a[i] - anmin));
      l[k]++;
    } 
    //printArray(l);
 
    for (k=1; k < m; k++) {
      l[k] += l[k-1];
    } 

    int hold = a[nmax];
    a[nmax]=a[0];
    a[0]=hold;
 
    int nmove = 0;
    int flash;
    j=0;
    k=m-1;
 
    while (nmove < n-1) {
      while (j > (l[k]-1)) {
        j++;
        k = (int) (c1 * (a[j] - anmin));
      } 
      flash = a[j]; 
      while (!(j == l[k])) {
        k = (int) (c1 * (flash - anmin));

        hold = a[l[k]-1];
        a[l[k]-1]=flash;
        flash = hold;

        l[k]--;
        nmove++;
      }
    }
 
    //printArray(a);
  }
 
  /**
  * Straight insertion sort
  */ 
  private static void insertionSort() {
    int i, j, hold; 
    for (i=a.length-3; i>=0; i--) {
      if (a[i+1] < a[i]) {
        hold = a[i];
        j=i; 
        while (a[j+1] < hold) {
          a[j] = a[j+1];
          j++;
        } 
        a[j] = hold;
      }
    } 
    //printArray(a);
  }
 
  /**
  * For checking sorting result and the distribution
  */ 
  private static void printArray(int[] ary) {
    for (int i=0; i < ary.length; i++) { 
      if ((i+1)%10 ==0)  
        System.out.println(ary[i]); 
      else 
        System.out.print(ary[i] + " ");
    } 
    System.out.println();
  }
}
