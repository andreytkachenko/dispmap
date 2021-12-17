use dispmap::compute;



fn main() -> anyhow::Result<()> {
    let mut args = std::env::args();
    let _ = args.next();
    
    let left_path = args.next().unwrap();
    let right_path = args.next().unwrap();

    println!("disparity for {} {}", left_path, right_path);

    let left  = image::open(left_path)?.to_rgb8();
    let right = image::open(right_path)?.to_rgb8();

    let disp = compute(&left, &right);
    
     disp.save("disp.png")?;

     Ok(())
}
