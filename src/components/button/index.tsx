
import type { IconProp } from '@fortawesome/fontawesome-svg-core';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import type { ButtonHTMLAttributes, MouseEvent, ReactNode } from 'react'; 

interface ButtonProps extends ButtonHTMLAttributes<HTMLButtonElement> {
  children?: ReactNode;
  variant?: 'primary' | 'secondary';
  icon?: IconProp;
  disabled?: boolean;
  onClick?: (event: MouseEvent<HTMLButtonElement>) => void;
}

export default function Button({
  children = null,
  variant = 'primary',
  disabled = false,
  onClick,
  icon,
}: ButtonProps) {
  return (
    <button
      type="button"
      className={`button button-${variant}`}
      onClick={onClick}
      disabled={disabled}
    >
      {icon ? (
        <span aria-hidden="true" style={{ marginRight: children ? '0.5rem' : 0 }}>
          <FontAwesomeIcon icon={icon} />
        </span>
      ) : null}
      {children}
    </button>
  );
}
