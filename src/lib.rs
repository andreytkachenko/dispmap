use image::{GrayImage, RgbImage};

fn diff(left_image: &RgbImage, right_image: &RgbImage, lx: u32, ly: u32, rx: u32, ry: u32) -> i32 {
    let r = (left_image.get_pixel(lx, ly)[0] as i8 - right_image.get_pixel(rx, ry)[0] as i8).abs()
        as i32;
    let g = (left_image.get_pixel(lx, ly)[1] as i8 - right_image.get_pixel(rx, ry)[1] as i8).abs()
        as i32;
    let b = (left_image.get_pixel(lx, ly)[2] as i8 - right_image.get_pixel(rx, ry)[2] as i8).abs()
        as i32;
    let color = (g - r).abs() + (b - g).abs();

    (r + g + b) + color * 4
}

fn match_pixels(left_image: &RgbImage, right_image: &RgbImage, x: u32, y: u32, j: u32) -> i32 {
    let mut error = 0;
    let ms = 4;
    let c = diff(left_image, right_image, x, y, x + j, y);
    let mut l = 0;
    let mut r = 0;
    let mut t = 0;
    let mut b = 0;

    error = c;

    for i in 1..=ms {
        l += diff(left_image, right_image, x - i, y, x + j - i, y);
        r += diff(left_image, right_image, x + i, y, x + j + i, y);
        t += diff(left_image, right_image, x, y - i, x + j, y - i);
        b += diff(left_image, right_image, x, y + i, x + j, y + i);
    }

    error += if l > r { r } else { l };
    error += if t > b { b } else { t };
    //error += l + r + b + t;

    error
}

fn get_pixel_color(image: &RgbImage, cursor: i32) -> f32 {
    if cursor == 0 {
        return 0.0;
    }

    (10 * image.width()) as f32 / (2.0 * 0.9 * cursor as f32)
}

fn get_pixel_hue(image: &RgbImage, x: u32, y: u32) -> i32 {
    let pixel = image.get_pixel(x, y);

    (pixel[1] as i32 - pixel[0] as i32).abs() + (pixel[2] as i32 - pixel[1] as i32).abs()
}

fn get_pixel_value(image: &RgbImage, x: u32, y: u32) -> i32 {
    let pixel = image.get_pixel(x, y);

    (pixel[0] as i32 + pixel[1] as i32 + pixel[2] as i32) / 3
}

fn exec(res: &mut GrayImage, left: &RgbImage, right: &RgbImage, line: u32) {
    let mut prev = 0;
    let mut preprev = 0;
    let mut cursor = 0i32;
    let mut precursor = 0i32;
    let mut preprecursor = 0i32;

    let window_size = 128u32;

    for x in 0..res.width() {
        let mut closest = -1i32;
        let mut min_error = -1i32;
        let mut matched = 0;

        let val = get_pixel_hue(left, x, line);

        for i in 1..window_size {
            let dist = (cursor - i as i32).abs();
            let tmp = match_pixels(left, right, x, line, i);
            let tmp_smoothed = tmp; // + (dist) * (1.0 / diff);

            if tmp_smoothed < min_error || min_error == -1 {
                min_error = tmp_smoothed;
                closest = i as i32;
                matched = 1;
            } else if tmp_smoothed == min_error
                && ((cursor - i as i32).abs() < (cursor - closest).abs())
            {
                closest = i as i32;
                matched += 1;
            }
        }

        if matched == 1 {
            cursor = closest;
        }

        res.put_pixel(x, line, ([get_pixel_color(left, cursor) as u8]).into());

        preprecursor = precursor;
        precursor = cursor;

        preprev = prev;
        prev = val;
    }
}

