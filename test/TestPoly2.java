package test;

class Dance {
     public void play(){
         System.out.println("Dance.play");
     }
     public void play(int i){
         System.out.println("Dance.play" + i);
     }
 }
 
 class Latin extends Dance {
    public void play(){
         System.out.println("Latin.play");
    }
     public void play(char c){
         System.out.println("Latin.play" + c);
     }
 }
 class Jazz extends Dance {
     public void play(){
         System.out.println("Jazz.play");
     }
     public void play(double d){
         System.out.println("Jazz.play" + d);
     }
 }

 public class TestPoly {
     public void perform(Dance dance){
         dance.play();
     }
     public static void main(String[] args){
         new TestPoly().perform(new Latin()); // Upcasting
         new TestPoly().perform(new Jazz()); // Upcasting
         new TestPoly().perform(new Dance()); // Upcasting
     }
 }
